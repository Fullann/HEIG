import {
  createContext,
  useContext,
  useRef,
  useState,
  useEffect,
  useCallback,
} from "react";

const PlayerContext = createContext();

export const PlayerProvider = ({ children }) => {
  const audioRef = useRef(null);
  const [trackList, setTrackList] = useState([]);
  const [currentIndex, setCurrentIndex] = useState(null);
  const [isPlaying, setIsPlaying] = useState(false);
  const [queue, setQueue] = useState([]);
  const [history, setHistory] = useState([]);
  const [currentTime, setCurrentTime] = useState(0);
  const [duration, setDuration] = useState(0);
  const [volume, setVolume] = useState(0.7);

  const playTrack = (tracks, index) => {
    // Ajouter la piste précédente à l'historique si elle existe
    if (currentIndex !== null && trackList.length > 0) {
      const currentTrack = trackList[currentIndex];
      setHistory(prev => {
        const newHistory = [currentTrack, ...prev];
        return newHistory.slice(0, 20); // Garder seulement les 20 dernières pistes
      });
    }

    setTrackList(tracks);
    setCurrentIndex(index);
    
    // Créer une nouvelle queue avec les pistes restantes
    const remainingTracks = tracks.slice(index + 1);
    setQueue(remainingTracks);
  };

  const addToQueue = (track) => {
    setQueue(prev => [...prev, track]);
  };

  const removeFromQueue = (index) => {
    setQueue(prev => prev.filter((_, i) => i !== index));
  };

  const playFromQueue = (queueIndex) => {
    const track = queue[queueIndex];
    const newQueue = queue.slice(queueIndex + 1);
    
    // Ajouter la piste actuelle à l'historique
    if (currentIndex !== null && trackList.length > 0) {
      const currentTrack = trackList[currentIndex];
      setHistory(prev => [currentTrack, ...prev.slice(0, 19)]);
    }

    // Mettre à jour la liste de lecture avec la piste de la queue
    setTrackList([track]);
    setCurrentIndex(0);
    setQueue(newQueue);
  };

  const next = useCallback(() => {
  if (queue.length > 0) {
    const track = queue[0];
    const newQueue = queue.slice(1);
    
    // Ajouter la piste actuelle à l'historique
    if (currentIndex !== null && trackList.length > 0) {
      const currentTrack = trackList[currentIndex];
      setHistory(prev => [currentTrack, ...prev.slice(0, 19)]);
    }
    
    setTrackList([track]);
    setCurrentIndex(0);
    setQueue(newQueue);
  } else if (currentIndex < trackList.length - 1) {
    setCurrentIndex(prev => prev + 1);
  }
}, [currentIndex, trackList, queue]);

const prev = useCallback(() => {
  if (history.length > 0) {
    const prevTrack = history[0];
    const newHistory = history.slice(1);
    
    if (currentIndex !== null && trackList.length > 0) {
      const currentTrack = trackList[currentIndex];
      setQueue(prev => [currentTrack, ...prev]);
    }
    
    setHistory(newHistory);
    setTrackList([prevTrack]);
    setCurrentIndex(0);
  } else if (currentIndex > 0) {
    setCurrentIndex(prev => prev - 1);
  }
}, [currentIndex, trackList, history]);


  const togglePlay = () => {
    const audio = audioRef.current;
    if (!audio) return;

    if (isPlaying) {
      audio.pause();
      setIsPlaying(false);
    } else {
      audio.play();
      setIsPlaying(true);
    }
  };

  const seek = (time) => {
    const audio = audioRef.current;
    if (audio) {
      audio.currentTime = time;
      setCurrentTime(time);
    }
  };

  const setVolumeLevel = (level) => {
    const audio = audioRef.current;
    if (audio) {
      audio.volume = level;
      setVolume(level);
    }
  };

  useEffect(() => {
    const audio = audioRef.current;
    if (!audio) return;

    const onPlay = () => setIsPlaying(true);
    const onPause = () => setIsPlaying(false);
    const onEnded = () => {
      setIsPlaying(false);
      next();
    };
    const onTimeUpdate = () => setCurrentTime(audio.currentTime);
    const onLoadedMetadata = () => {
      setDuration(audio.duration);
      setCurrentTime(0);
    };

    audio.addEventListener("play", onPlay);
    audio.addEventListener("pause", onPause);
    audio.addEventListener("ended", onEnded);
    audio.addEventListener("timeupdate", onTimeUpdate);
    audio.addEventListener("loadedmetadata", onLoadedMetadata);

    // Définir le volume initial
    audio.volume = volume;

    return () => {
      audio.removeEventListener("play", onPlay);
      audio.removeEventListener("pause", onPause);
      audio.removeEventListener("ended", onEnded);
      audio.removeEventListener("timeupdate", onTimeUpdate);
      audio.removeEventListener("loadedmetadata", onLoadedMetadata);
    };
  }, [next, volume]);

  useEffect(() => {
    if (currentIndex !== null && trackList.length > 0) {
      const audio = audioRef.current;
      if (audio) {
        audio.load();
        audio.play().catch((err) => console.error("Playback error:", err));
        setIsPlaying(true);
      }
    }
  }, [currentIndex, trackList]);

  return (
    <PlayerContext.Provider value={{
      audioRef,
      trackList,
      currentIndex,
      prev,
      next,
      togglePlay,
      isPlaying,
      currentTime,
      duration,
      seek,
      volume,
      setVolumeLevel,
      playTrack, // Ajouter cette fonction
      addToQueue,
      removeFromQueue,
      playFromQueue,
      queue,
      history
    }}>
      {children}
    </PlayerContext.Provider>
);

};

export const usePlayer = () => useContext(PlayerContext);