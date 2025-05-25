import { usePlayer } from "../context/PlayerContext";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPlay, faTimes } from "@fortawesome/free-solid-svg-icons";

export default function QueueSidebar() {
  const { 
    trackList, 
    currentIndex, 
    queue, 
    history, 
    playFromQueue, 
    removeFromQueue,
    playTrack 
  } = usePlayer();

  const currentTrack = trackList[currentIndex];


  return (
    <div className="queue-sidebar">
      <div className="queue-header">
        <div className="queue-title">File d'attente</div>
        <div className="queue-subtitle">
          {queue.length} piste{queue.length !== 1 ? 's' : ''} en attente
        </div>
      </div>

      <div className="queue-content">
        {/* Piste en cours */}
        {currentTrack && (
          <div className="queue-section">
            <div className="queue-section-title">En cours de lecture</div>
            <div className="queue-item current">
              <img
                src={currentTrack.album?.cover_small}
                alt={currentTrack.title}
                className="queue-item-cover"
              />
              <div className="queue-item-info">
                <div className="queue-item-title">{currentTrack.title}</div>
                <div className="queue-item-artist">{currentTrack.artist?.name}</div>
              </div>
            </div>
          </div>
        )}

        {/* File d'attente */}
        {queue.length > 0 && (
          <div className="queue-section">
            <div className="queue-section-title">À suivre</div>
            {queue.map((track, index) => (
              <div key={`queue-${track.id}-${index}`} className="queue-item">
                <img
                  src={track.album?.cover_small}
                  alt={track.title}
                  className="queue-item-cover"
                />
                <div className="queue-item-info">
                  <div className="queue-item-title">{track.title}</div>
                  <div className="queue-item-artist">{track.artist?.name}</div>
                </div>
                <div className="queue-item-actions">
                  <button
                    onClick={() => playFromQueue(index)}
                    className="control-btn"
                    title="Lire maintenant"
                  >
                    <FontAwesomeIcon icon={faPlay} />
                  </button>
                  <button
                    onClick={() => removeFromQueue(index)}
                    className="control-btn"
                    title="Retirer de la file"
                  >
                    <FontAwesomeIcon icon={faTimes} />
                  </button>
                </div>
              </div>
            ))}
          </div>
        )}

        {/* Historique */}
        {history.length > 0 && (
          <div className="queue-section">
            <div className="queue-section-title">Récemment joué</div>
            {history.slice(0, 10).map((track, index) => (
              <div 
                key={`history-${track.id}-${index}`} 
                className="queue-item"
                onClick={() => playTrack([track], 0)}
              >
                <img
                  src={track.album?.cover_small}
                  alt={track.title}
                  className="queue-item-cover"
                />
                <div className="queue-item-info">
                  <div className="queue-item-title">{track.title}</div>
                  <div className="queue-item-artist">{track.artist?.name}</div>
                </div>
              </div>
            ))}
          </div>
        )}

        {/* Message si aucune queue */}
        {queue.length === 0 && history.length === 0 && !currentTrack && (
          <div className="center-message">
            <p>Aucune piste en file d'attente</p>
          </div>
        )}
      </div>
    </div>
  );
}