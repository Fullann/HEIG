import { useParams, Link } from "react-router-dom";
import useSWR from "swr";
import TrackItem from "../components/TrackItem";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faSpinner, faArrowLeft, faPlay } from "@fortawesome/free-solid-svg-icons";
import { usePlayer } from "../context/PlayerContext";

const fetcher = (url) =>
  fetch(`http://localhost:8080${url}`).then((res) => res.json());

export default function PlaylistPage() {
  const { id } = useParams();
  const { data, error } = useSWR(`/playlist/${id}`, fetcher);
  const { playTrack } = usePlayer();

  if (error)
    return <div className="center-message">Impossible de charger la playlist</div>;

  if (!data)
    return (
      <div className="center-message">
        <FontAwesomeIcon icon={faSpinner} spin size="4x" />
      </div>
    );

  const handlePlayAll = () => {
    if (data.tracks.data.length > 0) {
      playTrack(data.tracks.data, 0);
    }
  };

  return (
    <div className="playlist-page">
      <Link to="/" className="back-link">
        <FontAwesomeIcon icon={faArrowLeft} />
      </Link>

      <div className="playlist-header">
        <img
          src={data.picture_medium}
          alt={data.title}
          className="playlist-cover"
        />
        <div className="playlist-info">
          <div className="playlist-meta">PLAYLIST</div>
          <h1>{data.title}</h1>
          <div className="playlist-meta">
            {data.tracks.data.length} piste{data.tracks.data.length !== 1 ? 's' : ''}
          </div>
        </div>
      </div>

      <div className="playlist-actions" style={{ marginBottom: '32px', display: 'flex', alignItems: 'center', gap: '16px' }}>
        <button 
          className="control-btn play-btn"
          onClick={handlePlayAll}
          style={{ padding: '16px', fontSize: '20px' }}
          title="Lire la playlist"
        >
          <FontAwesomeIcon icon={faPlay} />
        </button>
      </div>

      <div className="track-list">
        {data.tracks.data.map((track, i) => (
          <TrackItem
            key={track.id}
            track={track}
            index={i}
            trackList={data.tracks.data}
          />
        ))}
      </div>
    </div>
  );
}